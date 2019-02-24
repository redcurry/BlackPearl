using System;
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

            ViewModel = new MainViewModel();
            BindingContext = ViewModel;
        }

        public MainViewModel ViewModel { get; }

        private void MainPage_OnAppearing(object sender, EventArgs e)
        {
            ViewModel.Init();
            Canvas.InvalidateSurface();
        }

        private void Image_OnSizeChanged(object sender, EventArgs e)
        {
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

            var x = (float)(coin.X * scale);
            var y = (float)(coin.Y * scale);
            var r = (float)(coin.Radius * scale);

            canvas.DrawCircle(x, y, r, fillPaint);
            canvas.DrawCircle(x, y, r, strokePaint);
        }
    }
}
