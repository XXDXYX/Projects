using System;
using System.Collections.Generic;
using System.IO;
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
        
        string path = " ";
        string extension = Path.GetExtension(path).ToLowerInvariant();
        BookLoader loader = extension switch
        {
            ".epub" => new EpubBookLoader(),
           // ".fb2"  => new Fb2BookLoader(path),
            _       => throw new NotSupportedException($"Формат {extension} не підтримується")
        };
        BookDetailsView Book = loader.LoadBook(path);
    }
    
    
}