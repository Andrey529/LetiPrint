package com.example.backendservice.controller;

import com.example.backendservice.service.BackendService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.env.Environment;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class BackendController {

    BackendService backendService = new BackendService();

    @Autowired
    Environment env; //get path to file directory from command line

    // command: //java -jar target/BackendService-0.0.1-SNAPSHOT.jar --path=C:\Users\khama\Desktop\LetiPrint\BackendService\src\main\resources\storage
    @GetMapping("/downloadFile/{filename}")
    private ResponseEntity<?> getFile(@PathVariable String filename) {
        String envResponse = env.getProperty("path");
        return backendService.getFileFromLocalDirectory(envResponse, filename);
    }

}
