package com.example.backendservice.serelization;
import com.example.backendservice.models.MetaData;
import com.google.gson.Gson;
import com.google.gson.JsonObject;
import lombok.AllArgsConstructor;
@AllArgsConstructor
public class JsonSerelizator {

    public MetaData deserializeMetaDates(String metaData, String fileId){
        Gson gson = new Gson();
        JsonObject jsonObject = gson.fromJson(metaData, JsonObject.class);
        String filename = jsonObject.getAsJsonPrimitive("filename").toString();
        String fileLink = jsonObject.getAsJsonPrimitive("downloadLink").toString();
        String fileType = jsonObject.getAsJsonPrimitive("fileType").toString();
        String userId = jsonObject.getAsJsonPrimitive("userId").toString();
        MetaData metaDataFromJson = new MetaData();
        metaDataFromJson.setUserId(userId.substring(1,userId.length()-1));
        metaDataFromJson.setFileLink(fileLink.substring(1,fileLink.length()-1));
        metaDataFromJson.setFileName(filename.substring(1,filename.length()-1));
        metaDataFromJson.setFileId(Short.parseShort(fileId));
        metaDataFromJson.setFileType(fileType.substring(1,fileType.length()-1));
        return metaDataFromJson;

    }

    public String serializeJsonForIoTService(MetaData metaData){
        String json;
        Gson gson = new Gson();
        MetaData metaData1 = new MetaData();
        metaData1.setFileId(metaData.getFileId());
        metaData1.setUserId(metaData.getUserId());
        metaData1.setFileLink(metaData.getFileLink());
        metaData1.setFileType(metaData.getFileType());
        metaData1.setFileName(metaData.getFileName());
        json = gson.toJson(metaData1);
        return json;
    }



}
