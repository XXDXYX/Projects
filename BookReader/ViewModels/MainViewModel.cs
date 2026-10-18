using System.Collections.Generic;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;
namespace BookReader.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    [ObservableProperty]
    public partial List<BookDetailsView> Library { get;private set; } = new();

    [RelayCommand]
    void AddBook()
    {
        
    }
    
    
}