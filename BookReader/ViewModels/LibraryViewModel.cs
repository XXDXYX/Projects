using System;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
namespace BookReader.ViewModels;
public partial class LibraryViewModel:ViewModelBase
{
    
    [ObservableProperty]
    public partial ObservableCollection<BookDetailsView> Library { get; set; } = new();
    string filePath = "Library.txt";


    [RelayCommand]
    public void AddBook(string path)
    {
        if (string.IsNullOrEmpty(path))
            return;
        string extension = Path.GetExtension(path).ToLowerInvariant();
        BookLoader loader = extension switch
        {
            ".epub" => new EpubBookLoader(),
             ".fb2"  => new Fb2Book(),
                _   => throw new NotSupportedException($"Формат {extension} не підтримується")
        };
        BookDetailsView Book = loader.LoadBook(path);

        if (File.Exists(filePath))
        {
            if (!Library.Any(u => u.Path == Book.Path))
            {
                Library.Add(Book);

                SaveLibrary(Book.Path);
                Console.WriteLine($"Book added: {Book.Title}");
            }
        }
    }

    void SaveLibrary(string bookPath)
    {
        if(!File.ReadLines(filePath).Contains(bookPath)){ 
            File.AppendAllText(filePath, "\n" + bookPath);
        }
    }
}