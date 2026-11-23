using System.Collections.Generic;
using Avalonia.Media.Imaging;



namespace BookReader.ViewModels;

public abstract class BookContent : ViewModelBase
{
    
}

public enum ChapterType{Text,Image,PartTitle}

public class ContentBlock
{
    public ChapterType Type { get; set; }
    public string Text { set; get; }
    public Bitmap? Image { set; get; }
    public string PartTitle { set; get;}
}
public class Chapter
{ 
    public List<ContentBlock> Paragraphs { get; set; }

}


