using System.Diagnostics;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BookReader.ViewModels;

public partial class BookDetailsView:ViewModelBase
{
        [ObservableProperty] public partial string Autor { get;private set; }
        [ObservableProperty] public partial string Title { get;private set; }
        [ObservableProperty] public partial string Path { get;private set; }

        void InitBook()
        {
                
        }
        

}