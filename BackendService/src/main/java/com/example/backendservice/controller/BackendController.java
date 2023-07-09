package com.example.backendservice.controller;

import com.example.backendservice.BackendLogger;
import com.example.backendservice.models.MetaData;
import com.example.backendservice.serelization.JsonSerelizator;
import com.example.backendservice.service.BackendService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;


@RestController
@RequiredArgsConstructor
public class BackendController {

    private final BackendService backendService;

    private final JsonSerelizator jsonSerelizator = new JsonSerelizator();


    @GetMapping("/downloadFile")
    @ResponseBody
    private ResponseEntity<?> getFile(@RequestParam String fileId) {
        Map<String,String> mapOfRequestParam = new HashMap<>();
        mapOfRequestParam.put("fileId",fileId);
        try {
            MetaData metaData = backendService.getMetaDataByFileId(fileId);
            BackendLogger.loggingHttpRequest("Get", "/downloadFile", metaData.toString(), mapOfRequestParam);
            return new ResponseEntity<>(jsonSerelizator.serializeJsonForIoTService(metaData), HttpStatus.OK);
        }
        catch (Exception e) {
            BackendLogger.loggingUnsuccessfulRequest("Get","/downloadFile",null,mapOfRequestParam);
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        }
    }


    @PostMapping("/metaData")
    public String getUsersId(@RequestBody String metaData) {
        String fileId = backendService.teamIdGenerator(backendService.getFileIds());
        BackendLogger.loggingHttpRequest("Post", "/metaData", metaData,null);
        BackendLogger.loggingIdGenerator(fileId);
        backendService.save(jsonSerelizator.deserializeMetaDates(metaData,fileId));
        return fileId;
    }

}
