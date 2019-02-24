using Foundation;
using UIKit;

[assembly: Xamarin.Forms.Dependency(typeof(BlackPearl.Xamarin.iOS.ImageAnalysis))]
namespace BlackPearl.Xamarin.iOS
{
    public class ImageAnalysis : IImageAnalysis
    {
        public Coin FindCoin(byte[] jpg)
        {
            var ia = new global::ImageAnalysis.Bindings.ImageAnalysis();
            var imageData = NSData.FromArray(jpg);
            var image = UIImage.LoadFromData(imageData);
            var coinAsArray = ia.FindCoin(image);
            return new Coin
            {
                X = coinAsArray[0].DoubleValue,
                Y = coinAsArray[1].DoubleValue,
                Radius = coinAsArray[2].DoubleValue
            };
        }
    }
}