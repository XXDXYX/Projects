using System.Collections.Generic;
using VersOne.Epub;

namespace BookReader.ViewModels;

public abstract partial class BookContent : ViewModelBase
{
}

public class Chapter
{
    public List<string> Paragraphs = new();
    
}


public class EpubContent : BookContent
{
    public List<Chapter> Chapters = new ();
    
}
