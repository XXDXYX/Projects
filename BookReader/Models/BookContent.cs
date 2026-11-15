using System.Collections.Generic;


namespace BookReader.ViewModels;

public abstract partial class BookContent : ViewModelBase
{
}

public class Chapter
{
    public List<string> Paragraphs { get; set; } = new();

}


public class EpubContent : BookContent
{
    public List<Chapter> Chapters = new ();
    
}
