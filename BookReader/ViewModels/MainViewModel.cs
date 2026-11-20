using System.Collections.Generic;
using System.IO;
using System.Text.Json;
using System;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;


namespace BookReader.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    public MainViewModel()
    {
        CurentPage = LibraryClass;

        if (File.Exists(filePath))
        {
            string[] lines = File.ReadAllLines(filePath);
            foreach (var i in lines)
            {
                if (!string.IsNullOrWhiteSpace(i))
                {
                    LibraryClass.AddBook(i);
                }
            }

            
        }
       
    }

    [ObservableProperty]
    public partial ViewModelBase? CurentPage { get; set;}
    public  LibraryViewModel? LibraryClass { get; } = new();
    public BookReaderViewModel? ReaderClass { get; } = new();
    private string filePath = "Library.txt";
    
    [RelayCommand]
    public void AddBook(string path)
    {
        if (string.IsNullOrEmpty(path))
            return;

        string extension = Path.GetExtension(path).ToLowerInvariant();
        BookLoader loader = extension switch
        {
            ".epub" => new EpubBookLoader(),
            ".fb2"  => new Fb2Book(path),
            _ => throw new NotSupportedException($"Формат {extension} не підтримується")
        };

        BookDetailsView book = loader.LoadBook(path);
        LibraryClass.Library.Add(book);
        Console.WriteLine($"Book added: {book.Title}");
    }
    [RelayCommand]
    public void OnBookClicked(BookDetailsView book)
    {
        ReaderClass.book = book;
        Console.WriteLine(ReaderClass.book.Author);
        CurentPage = ReaderClass;
        
    }
    
}