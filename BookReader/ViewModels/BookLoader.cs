using VersOne.Epub;

namespace BookReader.ViewModels;

public abstract class BookLoader:ViewModelBase
{
    
    public abstract BookDetailsView LoadBook(string path);
}

public class EpubBookLoader:BookLoader
{
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
            Book.Autor = epubBook.Author;
        }
        else
        {
            Book.Autor = "Unknown Autor";
        }
        
        Book.Path = path;
        
        if (epubBook.CoverImage != null)
        {
            Book.Image = epubBook.CoverImage;
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