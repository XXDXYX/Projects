using VersOne.Epub;

namespace BookReader.ViewModels;

public abstract class BookContent<T>:ViewModelBase
{
    public T Content { get; set; }
}

public class EpubContent : BookContent<VersOne.Epub.EpubContent>
{
    
}
