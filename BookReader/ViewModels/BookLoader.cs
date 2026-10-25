using System.IO;
using Avalonia.Media.Imaging;
using VersOne.Epub;

namespace BookReader.ViewModels;

public abstract class BookLoader:ViewModelBase
{
    
    public abstract BookDetailsView LoadBook(string path);
}

public class EpubBookLoader:BookLoader
{
    
   
    private static Bitmap? ToBitmap(byte[]? bytes)
    {
        if (bytes is null || bytes.Length == 0)
            return null;

        using var stream = new MemoryStream(bytes);
        return new Bitmap(stream);
    }
     public override BookDetailsView LoadBook(string path)
    {
        EpubBook epubBook = EpubReader.ReadBook(path);
        BookDetailsView Book = new();
        EpubContent Content = new();
        if (epubBook.Title != null)
        {
            Book.Title = epubBook.Title;
        }
        else
        {
            Book.Title = "Unknown Title";
        }

        if (epubBook.Author != null)
        {
            Book.Author = epubBook.Author;
        }
        else
        {
            Book.Author = "Unknown Autor";
        }
        
        Book.Path = path;
        
        if (epubBook.CoverImage != null)
        {

            Book.Image = ToBitmap(epubBook.CoverImage);
        }
        else
        {
            Book.Image = null;
        }

        Content.Content = epubBook.Content;
        Book.Content = Content;
        
        
        return Book;
    }
}