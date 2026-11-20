using System.Collections.Generic;
using System.Collections.ObjectModel;
using Avalonia.Media.Imaging;
using CommunityToolkit.Mvvm.ComponentModel;


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


