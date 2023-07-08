package Helpers;

import javafx.concurrent.Task;

import java.io.File;

public class FormatUpdater extends Task<Integer> {
    private String folder;
    public FormatUpdater(String folder){
        this.folder = folder;
    }
    @Override
    protected Integer call() throws Exception {
        File updatedFolder = new File(folder);
        if (updatedFolder.exists()){
            File[] list = updatedFolder.listFiles(File::isFile);
            if (list != null) {
                int len = list.length;
                int i = 0;
                for (File f : list) {
                    if (f.getName().matches("\\.+\\.c\\n")) {
                        BMPSaver.updateSavedFile(f.toString());
                        this.updateProgress(++i,len);
                    }
                }
            } else {
                return 0;
            }
        }
        return 1;
    }
}
