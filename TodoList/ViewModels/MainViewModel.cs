using System;
using System.Collections.Generic;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using static TodoList.NoteModelView;
namespace TodoList.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    private List<NoteModelView> _notes = new List<NoteModelView>();
    [ObservableProperty] public partial string _task { get; set; } = "";

    [RelayCommand]
    void addNote()
    {
        string text = _task;
        if (string.IsNullOrWhiteSpace(text))
        {
            return;
        }

        var note = new NoteModelView { Content = text };
        _notes.Add(note);
        Console.WriteLine(text);
        _task = "";
    }

    void showList()
    {
        
    }
    

}