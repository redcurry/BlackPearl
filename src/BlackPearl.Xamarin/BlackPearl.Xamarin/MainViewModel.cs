using GalaSoft.MvvmLight;

namespace BlackPearl.Xamarin
{
    public class MainViewModel : ViewModelBase
    {
        private readonly BlackPearlApp _app;

        public MainViewModel(BlackPearlApp app)
        {
            _app = app;
        }

        private Image _image;
        public Image Image
        {
            get => _image;
            set => Set(ref _image, value);
        }

        private Coin _coin;
        public Coin Coin
        {
            get => _coin;
            set => Set(ref _coin, value);
        }

        public void LoadImage(Image image)
        {
            _app.LoadImage(image);
            _app.Analyze();

            Image = image;
            Coin = _app.GetCoin();
        }
    }
}