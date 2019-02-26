using Xamarin.Forms;
using Xamarin.Forms.Xaml;

[assembly: XamlCompilation(XamlCompilationOptions.Compile)]
namespace BlackPearl.Xamarin
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();

            var imageAnalysis = DependencyService.Get<IImageAnalysis>();
            var app = new BlackPearlApp(imageAnalysis);
            var mainVm = new MainViewModel(app);
            var mainPage = new MainPage();
            mainPage.ViewModel = mainVm;

            MainPage = mainPage;
        }

        protected override void OnStart()
        {
            // Handle when your app starts
        }

        protected override void OnSleep()
        {
            // Handle when your app sleeps
        }

        protected override void OnResume()
        {
            // Handle when your app resumes
        }
    }
}
