using System;
using System.IO;
using System.Reflection;
using SkiaSharp;
using SkiaSharp.Views.Forms;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private MainViewModel _viewModel;
        public MainViewModel ViewModel
        {
            get => _viewModel;
            set
            {
                _viewModel = value;
                BindingContext = ViewModel;
            }
        }

        private void MainPage_OnAppearing(object sender, EventArgs e)
        {
            var image = new Image
            {
                Bytes = GetFirstResourceAsBytes()
            };

            ViewModel.LoadImage(image);
            Canvas.InvalidateSurface();
        }

        private void Canvas_OnPaintSurface(object sender, SKPaintSurfaceEventArgs e)
        {
            var imageControl = ApertureImage;
            var scale = e.Info.Width / 480;
            var coin = ViewModel.Coin;
            if (coin == null) return;

            var canvas = e.Surface.Canvas;
            canvas.Clear();

            var fillPaint = new SKPaint
            {
                Style = SKPaintStyle.Fill,
                Color = new SKColor(255, 0, 0, 128),
                StrokeWidth = 2.0f,
            };

            var strokePaint = new SKPaint
            {
                Style = SKPaintStyle.Stroke,
                Color = Color.Red.ToSKColor(),
                StrokeWidth = 2.0f,
            };

            var x = (float)(coin.CenterX * scale);
            var y = (float)(coin.CenterY * scale);
            var r = (float)(coin.Radius * scale);

            canvas.DrawCircle(x, y, r, fillPaint);
            canvas.DrawCircle(x, y, r, strokePaint);
        }

        private Stream GetFirstResourceAsStream()
        {
            var assembly = Assembly.GetExecutingAssembly();
            var resourceNames = assembly.GetManifestResourceNames();
            return assembly.GetManifestResourceStream(resourceNames[0]);
        }

        private byte[] GetFirstResourceAsBytes()
        {
            var assembly = Assembly.GetExecutingAssembly();
            var resourceNames = assembly.GetManifestResourceNames();
            using (var resourceStream = assembly.GetManifestResourceStream(resourceNames[0]))
            {
                return ToBytes(resourceStream);
            }
        }

        private byte[] ToBytes(Stream stream)
        {
            var length = stream.Length;
            var bytes = new byte[length];
            stream.Read(bytes, 0, (int)length);
            return bytes;
        }
    }
}
