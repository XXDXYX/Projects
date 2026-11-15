using System;
using System.Collections.ObjectModel;
using System.IO;
using Avalonia.Controls;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
namespace BookReader.ViewModels;
public partial class LibraryViewModel:ViewModelBase
{
    
    [ObservableProperty]
    public partial ObservableCollection<BookDetailsView> Library { get; set; } = new();
    


    [RelayCommand]
    public void AddBook(string path)
    {
        if (string.IsNullOrEmpty(path))
            return;
        string extension = Path.GetExtension(path).ToLowerInvariant();
        BookLoader loader = extension switch
        {
            ".epub" => new EpubBookLoader(),
            // ".fb2"  => new Fb2BookLoader(path),
            _       => throw new NotSupportedException($"Формат {extension} не підтримується")
        };
        BookDetailsView Book = loader.LoadBook(path);
        Library.Add(Book);
        Console.WriteLine($"Book added: {Book.Title}");
    }
    
    
}