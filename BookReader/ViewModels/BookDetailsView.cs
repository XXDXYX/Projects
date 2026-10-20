using System.Diagnostics;
using System.Linq;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BookReader.ViewModels;

public partial class BookDetailsView:ViewModelBase
{
        [ObservableProperty] public partial string Autor { get; set; }
        [ObservableProperty] public partial string Title { get; set; }
        [ObservableProperty] public partial string Path { get; set; }
        
        [ObservableProperty]
        public partial byte[]? Image { get; set;} 
        
        [ObservableProperty] public partial BookContent<VersOne.Epub.EpubContent> Content { get; set; }


}