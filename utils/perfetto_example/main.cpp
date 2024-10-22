#include "perfetto.h"
#include <fstream>
#include <iostream>

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("Dummy").SetDescription("Dummy events"));

PERFETTO_TRACK_EVENT_STATIC_STORAGE();

void dummy_function() {
  TRACE_EVENT("Dummy", "dummy_function");
  std::cout << "Dummy function" << std::endl;
}

void dummy_loop() {
  TRACE_EVENT("Dummy", "dummy_loop");
  for (int i = 0; i < 100; i++) {
    dummy_function();
  }
}

std::unique_ptr<perfetto::TracingSession> StartTracing() {
  // The trace config defines which types of data sources are enabled for
  // recording. In this example we just need the "track_event" data source,
  // which corresponds to the TRACE_EVENT trace points.
  perfetto::TraceConfig cfg;
  cfg.add_buffers()->set_size_kb(1024);
  auto *ds_cfg = cfg.add_data_sources()->mutable_config();
  ds_cfg->set_name("track_event");
  auto tracing_session = perfetto::Tracing::NewTrace();
  tracing_session->Setup(cfg);
  tracing_session->StartBlocking();
  return tracing_session;
}
void StopTracing(std::unique_ptr<perfetto::TracingSession> tracing_session) {
  // Make sure the last event is closed for this example.
  perfetto::TrackEvent::Flush();
  // Stop tracing and read the trace data.
  tracing_session->StopBlocking();
  std::vector<char> trace_data(tracing_session->ReadTraceBlocking());
  // Write the result into a file.
  // Note: To save memory with longer traces, you can tell Perfetto to write
  // directly into a file by passing a file descriptor into Setup() above.
  std::ofstream output;
  output.open("example.pftrace", std::ios::out | std::ios::binary);
  output.write(&trace_data[0], std::streamsize(trace_data.size()));
  output.close();
  PERFETTO_LOG("Trace written in example.pftrace file. To read this trace in "
               "text form, run `./tools/traceconv text example.pftrace`");
}

int main(int argc, char **argv) {
  perfetto::TracingInitArgs args;

  // 1) The in-process backend only records within the app itself.
  args.backends |= perfetto::kInProcessBackend;

  // 2) The system backend writes events into a system Perfetto daemon
  // args.backends |= perfetto::kSystemBackend;

  perfetto::Tracing::Initialize(args);
  perfetto::TrackEvent::Register();

  auto tracing_session = StartTracing();
  // Give a custom name for the traced process.
  perfetto::ProcessTrack process_track = perfetto::ProcessTrack::Current();
  perfetto::protos::gen::TrackDescriptor desc = process_track.Serialize();
  desc.mutable_process()->set_process_name("Example");
  perfetto::TrackEvent::SetTrackDescriptor(process_track, desc);

  dummy_loop();

  StopTracing(std::move(tracing_session));
  return 0;
}
