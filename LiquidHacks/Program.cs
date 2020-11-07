using System;
using System.Threading;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Logging.Serilog;

namespace LiquidHacks {
    class Program {
        // Initialization code. Don't use any Avalonia, third-party APIs or any
        // SynchronizationContext-reliant code before AppMain is called: things aren't initialized
        // yet and stuff might break.
        public static void Main(string[] args) {

            Thread UI = new Thread(new ParameterizedThreadStart(StartUIThread));
            UI.Start(args);
        }

        // Avalonia configuration, don't remove; also used by visual designer.
        public static AppBuilder BuildAvaloniaApp()
            => AppBuilder.Configure<App>()
                .UsePlatformDetect()
                .LogToDebug();

        public static void StartUIThread(object sender) {
            BuildAvaloniaApp().StartWithClassicDesktopLifetime((string[]) sender);
        }
    }
}
