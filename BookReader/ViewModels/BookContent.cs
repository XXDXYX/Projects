using VersOne.Epub;

namespace BookReader.ViewModels;

public abstract class BookContent : ViewModelBase
{
}

public abstract class BookContent<T> : BookContent
{
    public T? Content { get; set; }
}

public class EpubContent : BookContent<VersOne.Epub.EpubContent>
{
    
}
