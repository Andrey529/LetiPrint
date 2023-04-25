package com.example.letiprintbot.metaData;

import com.google.gson.Gson;
import org.json.JSONObject;

public class MetaData {
    String downloadLink;
    String filename;
    String fileType;
    String userId;
    public JSONObject makeJson(String botToken, String filePath, String filename, String userId){
        addDownloadLink(botToken,filePath);
        addFilename(filename);
        addFileType(filename);
        addUserId(userId);
        Gson gson = new Gson();
        String json = gson.toJson(this);
        JSONObject jObj = new JSONObject(json);
        return jObj;
    }

    public void addDownloadLink(String botToken, String filePath){
        this.downloadLink = "https://api.telegram.org/file/bot" + botToken + "/" + filePath.substring(1, filePath.length() - 1);

    }

    public void addFilename(String filename){
        int extensionIndex = filename.lastIndexOf(".");
        this.filename = filename.substring(0,extensionIndex);
    }

    public void addFileType(String filePath){
        int extensionIndex = filePath.lastIndexOf(".");
        this.fileType = filePath.substring(extensionIndex + 1);
    }

    public void addUserId(String userId){
        this.userId = userId;
    }

}
