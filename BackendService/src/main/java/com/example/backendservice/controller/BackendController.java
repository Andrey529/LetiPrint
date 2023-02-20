package com.example.backendservice.controller;

import com.example.backendservice.service.BackendService;
import org.springframework.core.io.InputStreamResource;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.nio.file.Path;
import java.nio.file.Paths;

@RestController
public class BackendController {

    BackendService backendService;

    @GetMapping("/downloadFile/{filename}")
    private ResponseEntity<?> getFile(@PathVariable String filename) throws FileNotFoundException {
        File file = new File("C:\\Users\\khama\\Desktop\\storage\\test.txt");
        InputStreamResource i = new InputStreamResource(new FileInputStream(file));
            return ResponseEntity.ok()
                    .header("fileName",file.getName())
                    .contentType(MediaType.parseMediaType("application/octet-stream"))
                    .body(i);
    }

}
