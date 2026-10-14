using System;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using TodoList.ViewModels;

namespace TodoList;

public partial class NoteModelView: ViewModelBase
{
     [ObservableProperty] public partial string Content { get; set; }
     [ObservableProperty] public partial bool isTaskPin { get; set; } = false;

     

}