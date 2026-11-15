using System.Collections.Generic;
using System.IO;
using Avalonia.Media.Imaging;
using VersOne.Epub;
using HtmlAgilityPack;
using VersOne.Epub.Options;

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

    private List<Chapter> GetChapters(EpubBook epubBook)
    {
        var chapters = new List<Chapter>();

        foreach (var file in epubBook.ReadingOrder)
        {
            var paragraphs = ParseParagraphs(file.Content);

            chapters.Add(new Chapter
            { 
                Paragraphs = paragraphs
            });
        }

        return chapters;                    
        
    }

    private List<string> ParseParagraphs(string fileContent)
    {
        
        var doc = new HtmlDocument();
        doc.LoadHtml(fileContent);                              

        var paragraphs = new List<string>();
        var nodes = doc.DocumentNode.SelectNodes("//p");

        if (nodes != null)                               
        {
            foreach (var node in nodes)
                paragraphs.Add(node.InnerText.Trim());   
        }

        return paragraphs;
    }

    public override BookDetailsView LoadBook(string path)
    {
        EpubBook epubBook = EpubReader.ReadBook(path, EpubReaderOptionsPreset.IGNORE_ALL_ERRORS);
        BookDetailsView Book = new();
      
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
        
        Book.Content = GetChapters(epubBook);
        
        return Book;
    }
}