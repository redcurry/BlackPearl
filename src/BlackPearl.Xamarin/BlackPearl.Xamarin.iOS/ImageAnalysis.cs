using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Foundation;
using UIKit;

[assembly: Xamarin.Forms.Dependency(typeof(BlackPearl.Xamarin.iOS.ImageAnalysis))]
namespace BlackPearl.Xamarin.iOS
{
    public class ImageAnalysis : IImageAnalysis
    {
        public double GetMean()
        {
            return new global::ImageAnalysis.Bindings.ImageAnalysis().GetMean();
        }
    }
}