
namespace BookReader.Views;

using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Platform.Storage;
using BookReader.ViewModels;

public partial class LibraryView : UserControl
{
    public LibraryView()
    {
        InitializeComponent();
    }

    private async void OpenButton_Click(object? sender, RoutedEventArgs e)
    {
        var topLevel = TopLevel.GetTopLevel(this);
        if (topLevel is null)
        {
            return;
        }

        var files = await topLevel.StorageProvider.OpenFilePickerAsync(new FilePickerOpenOptions
        {
            Title = "Оберіть книжку",
            AllowMultiple = false,
            FileTypeFilter = new[]
            {
                new FilePickerFileType("Книги") { Patterns = new[] { "*.epub", "*.fb2"} }
               
            }
        });

        if (files.Count == 0)
        {
            return;
        }

        if (DataContext is LibraryViewModel viewModel)
        {
            viewModel.AddBook(files[0].Path.LocalPath);
        }
    }
}