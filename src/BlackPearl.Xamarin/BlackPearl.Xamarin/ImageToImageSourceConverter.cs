using System;
using System.Globalization;
using System.IO;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public class ImageToImageSourceConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is Image image)
                return ImageSource.FromStream(() => new MemoryStream(image.Bytes));
            return null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return null;
        }
    }
}