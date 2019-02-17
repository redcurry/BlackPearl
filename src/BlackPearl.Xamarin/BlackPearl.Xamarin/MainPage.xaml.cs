using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();

            var analysis = DependencyService.Get<IImageAnalysis>();
            var imageBytes = GetFirstResourceAsBytes();

            Content = new Image
            {
                Source = ImageSource.FromStream(() => analysis.DrawOn(imageBytes))
            };
        }

        public byte[] GetFirstResourceAsBytes()
        {
            var assembly = Assembly.GetExecutingAssembly();
            var resourceNames = assembly.GetManifestResourceNames();
            using (var resourceStream = assembly.GetManifestResourceStream(resourceNames[0]))
            {
                return ToBytes(resourceStream);
            }
        }

        public byte[] ToBytes(Stream stream)
        {
            var length = stream.Length;
            var bytes = new byte[length];
            stream.Read(bytes, 0, (int)length);
            return bytes;
        }
    }
}
