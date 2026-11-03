using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Platform.Storage;
using BookReader.ViewModels;

namespace BookReader.Views;

public partial class MainWindow : Window
{

    public MainWindow()
    {
        InitializeComponent();
    }
        private async void OpenButton_Click(object? sender, RoutedEventArgs e)
        {
            
            var files = await StorageProvider.OpenFilePickerAsync(new FilePickerOpenOptions
            {
                Title = "Оберіть книжку",
                AllowMultiple = false,
                FileTypeFilter = new[]
                {
                    new FilePickerFileType("Книжки") { Patterns = new[] { "*.epub", "*.fb2", "*.pdf" } }
                }
            });
    
            if (files.Count == 0) return;          
    
            string path = files[0].Path.LocalPath; 
            if (DataContext is MainViewModel vm)     
            {
                vm.LibraryClass.AddBook(path);
            }
        }
}