using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

using Foundation;
using UIKit;

[assembly: Xamarin.Forms.Dependency(typeof(BlackPearl.Xamarin.iOS.ImageAnalysis))]
namespace BlackPearl.Xamarin.iOS
{
    public class ImageAnalysis : IImageAnalysis
    {
        public Stream DrawOn(byte[] jpg)
        {
            var ia = new global::ImageAnalysis.Bindings.ImageAnalysis();
            var imageData = NSData.FromArray(jpg);
            var image = UIImage.LoadFromData(imageData);
            var newImage = ia.DrawOn(image);
            return newImage.AsPNG().AsStream();
        }
    }
}