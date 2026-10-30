using System.Collections.Generic;
using Avalonia.Media.Imaging;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BookReader.ViewModels;

public partial class BookDetailsView : ViewModelBase
{
    [ObservableProperty]
    public partial string Author { get; set; }

    [ObservableProperty]
    public partial string Title { get; set; }

    [ObservableProperty]
    public partial string Path { get; set; }

    [ObservableProperty]
    public partial Bitmap? Image { get; set; }

    [ObservableProperty]
    public partial List<Chapter> Content { get; set; }
    
    
    
}