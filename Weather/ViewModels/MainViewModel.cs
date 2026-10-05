using CommunityToolkit.Mvvm.ComponentModel;

namespace Weather.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    [ObservableProperty] public partial string Greeting { get; set; } = "Hello World!";
}