
using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using BookReader.Views;
using CommunityToolkit.Mvvm.ComponentModel;


namespace BookReader.ViewModels;



public partial class MainViewModel : ViewModelBase
{
    public MainViewModel()
    {
        CurentPage = LibraryClass;

        if (!File.Exists(Books))
            return;
        string jsonFromLines = File.ReadAllText(Books);
        var restoredBook = JsonSerializer.Deserialize<List<BookDetailsView>>(jsonFromLines);
        if (restoredBook is null)
            return;

        foreach (var i in restoredBook)
        {
            LibraryClass.Library.Add(i);
        }
    }

    [ObservableProperty]
    public partial ViewModelBase? CurentPage { get; set;}
    public LibraryViewModel LibraryClass { get; } = new();
    public BookReaderPageView ReaderClass { get; } = new();
    private string Books = "library.json";

    
}
   
    
    
