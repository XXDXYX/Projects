using System.Collections.Generic;
using Avalonia.Media.Imaging;



namespace BookReader.ViewModels;

public abstract class BookContent : ViewModelBase
{
    
}

public enum ChapterType{Text,Image}

public class ContentBlock
{
    public ChapterType Type { get; set; }
    public string Text { set; get; }
    public Bitmap? Image { set; get; }
}
public class Chapter
{ 
    public List<ContentBlock> Paragraphs { get; set; }

}


