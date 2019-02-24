using System.IO;
using System.Reflection;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public class MainViewModel
    {
        public MainViewModel()
        {
            Image = ImageSource.FromStream(GetFirstResourceAsStream);
        }

        public ImageSource Image { get; set; }
        public Coin Coin { get; set; }

        public void Init()
        {
            var analysis = DependencyService.Get<IImageAnalysis>();
            var imageBytes = GetFirstResourceAsBytes();
            Coin = analysis.FindCoin(imageBytes);
        }

        public Stream GetFirstResourceAsStream()
        {
            var assembly = Assembly.GetExecutingAssembly();
            var resourceNames = assembly.GetManifestResourceNames();
            return assembly.GetManifestResourceStream(resourceNames[0]);
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