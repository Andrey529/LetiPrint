package com.example.backendservice.service;


import com.example.backendservice.repositories.MetaDataRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Objects;


@Service
@RequiredArgsConstructor
public class BackendService {


    public String teamIdGenerator(List<Short> listOfFileId) {
        int firstNumber = (int) Math.round(Math.random() * 9);
        int secondNumber = (int) Math.round(Math.random() * 9);
        int thirdNumber = (int) Math.round(Math.random() * 9);
        int fourthNumber = (int) Math.round(Math.random() * 9);
        String id =  firstNumber + Integer.toString(secondNumber)
                + thirdNumber + fourthNumber;
        for (int i = 0; i < listOfFileId.size(); i++) {
            if (Objects.equals(id, listOfFileId.get(i))) {
                id = teamIdGenerator(listOfFileId);

            }
        }
        return id;
    }

}