using System.Diagnostics;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BookReader.ViewModels;

public partial class BookDetailsView:ViewModelBase
{
        [ObservableProperty] public partial string Autor { get; set; }
        [ObservableProperty] public partial string Name { get; set; }


}