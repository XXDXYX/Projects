using System;
using System.Linq;
using System.Text.Json;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using static TodoList.NoteModelView;
namespace TodoList.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    [ObservableProperty] public ObservableCollection<NoteModelView> _notes = new ObservableCollection<NoteModelView>();
    [ObservableProperty] public partial string _task { get; set; } = "";
    string filePath = "notes.json";
    public MainViewModel()
    {
         if (!File.Exists(filePath))
                        return;
         string jsonFromLines = File.ReadAllText(filePath);
         var restoredNote = JsonSerializer.Deserialize<List<NoteModelView>>(jsonFromLines);  
        if (restoredNote is null)
             return;
        foreach (var note in restoredNote)
        {
            _notes.Add(note);
        }
    }

    void Save()
    {
        string json = JsonSerializer.Serialize(Notes);  
        File.WriteAllText(filePath, json);   
    }
    
    [RelayCommand]
    void AddNote()
    {
        string text = _task;
        if (string.IsNullOrWhiteSpace(text))
        {
            return;
        }

        var note = new NoteModelView { Content = text };
        _notes.Add(note);
        _task = "";
        Save();
    }

    [RelayCommand]
    void DeleteNote(NoteModelView note)
    {
        int index = Notes.IndexOf(note);
        _notes.RemoveAt(index);
        Save();
    }
    
    [RelayCommand]void PinNote(NoteModelView note)
    {
        note.isTaskPin = !note.isTaskPin;
        int oldIndex = Notes.IndexOf(note);
        int newIndex = note.isTaskPin ? 0 : Notes.Count(n => n.isTaskPin);
        Notes.Move(oldIndex, newIndex);
        Save();
    }
   
}