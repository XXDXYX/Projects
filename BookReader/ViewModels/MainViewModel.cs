using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Text.Json;
using System.Runtime.InteropServices;
using Avalonia.Interactivity;
using Avalonia.Platform.Storage;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Win32;

namespace BookReader.ViewModels;



public partial class MainViewModel : ViewModelBase
{
    public LibraryViewModel LibraryClass { get; } = new();
    private string Books = "library.json";
    public MainViewModel()
    {
        if (!File.Exists(Books))
            return;
        string jsonFromLines = File.ReadAllText(Books);
        var restoredBook = JsonSerializer.Deserialize<List<BookDetailsView>>(jsonFromLines);  
        if (restoredBook is null)
            return;
        
        foreach (var i in restoredBook)
        {
           LibraryClass.Library.Add(i);
        }
    }
   
    
    
}