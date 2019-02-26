using System.IO;
using System.Reflection;

namespace BlackPearl.Xamarin
{
    public class BlackPearlApp
    {
        private readonly IImageAnalysis _imageAnalysis;

        private Image _image;
        private Coin _coin;

        public BlackPearlApp(IImageAnalysis imageAnalysis)
        {
            _imageAnalysis = imageAnalysis;
        }

        public void LoadImage(Image image)
        {
            _image = image;
        }

        public void Analyze()
        {
            _coin = _imageAnalysis.FindCoin(_image.Bytes);
        }

        public Coin GetCoin()
        {
            return _coin;
        }
    }
}
