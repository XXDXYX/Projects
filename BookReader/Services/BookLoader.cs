using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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
            
            var paragraphs = ParseParagraphs(file.Content,epubBook);

            chapters.Add(new Chapter
            { 
                Paragraphs = paragraphs
            });
        }

        return chapters;                    
        
    }

    private List<ContentBlock> ParseParagraphs(string fileContent, EpubBook epubBook)
    {
        List<ContentBlock> Paragraphs = new();
        var doc = new HtmlDocument();
        doc.LoadHtml(fileContent);
        
        var nodes = doc.DocumentNode.SelectNodes("//p | //img | //svg/img");
        
    
        if (nodes != null)                               
        {
            foreach (var node in nodes)
                if (node.Name == "p")
                {
                    ContentBlock contentBlock = new();
                    contentBlock.Type = ChapterType.Text;
                    contentBlock.Text = node.InnerText.Trim();
                    Paragraphs.Add(contentBlock);
                }
                else if (node.Name == "img" || node.Name == "image")
                {
                    ContentBlock contentBlock = new();
                    contentBlock.Type = ChapterType.Image;
                    string imageUrl = null;
                    if (node.Name == "img")
                    { 
                         imageUrl = node.GetAttributeValue("src", "");
                    }else if (node.Name == "image")
                    {
                        imageUrl = node.GetAttributeValue("xlink:href", node.GetAttributeValue("href", ""));
                    }
                    
                    
                    if (!string.IsNullOrEmpty(imageUrl))
                    {
                        string cleanSrc = Uri.UnescapeDataString(imageUrl.Split('#')[0]);
                        
                        string fileName = Path.GetFileName(cleanSrc);
                        
                        var image = epubBook.Content.Images.Local
                            .FirstOrDefault(img => Path.GetFileName(img.FilePath)
                                .Equals(fileName, StringComparison.OrdinalIgnoreCase));

                        if (image != null)
                        {
                            byte[] imageBytes = image.Content;
                            contentBlock.Image = ToBitmap(imageBytes);
                        }
                    }
                    
                    
                    Paragraphs.Add(contentBlock);
                    
                }
                    
        }

        return Paragraphs;
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