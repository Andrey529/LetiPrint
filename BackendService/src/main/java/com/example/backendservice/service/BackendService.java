package com.example.backendservice.service;


import com.example.backendservice.BackendLogger;
import com.example.backendservice.models.MetaData;
import com.example.backendservice.repositories.MetaDataRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import java.sql.Timestamp;
import java.util.List;
import java.util.Objects;


@Service
@RequiredArgsConstructor
public class BackendService {

    @Autowired
    private final MetaDataRepository metaDataRepository;

    public List<Short> getFileIds(){
        return metaDataRepository.getFileIds();
    }

    public void save(MetaData metaData){
        long currentTimeMillis = System.currentTimeMillis();
        Timestamp timestamp = new Timestamp(currentTimeMillis);
        metaData.setCreatedAt(timestamp);
        metaDataRepository.save(metaData);

    }

    @Scheduled(fixedRate = 12*60*60*1000)
    public void deleteOldRecords(){
        int countOfLines = metaDataRepository.countOfLines();
        metaDataRepository.deleteOldRecords();
        countOfLines -= metaDataRepository.countOfLines();
        BackendLogger.loggingDeleteOldRecordsFromDb(countOfLines);
    }

    public MetaData getMetaDataByFileId(String fileId){
        return metaDataRepository.getMetaDataByFileId(fileId);
    }

    public String teamIdGenerator(List<Short> listOfFileId) {
        int firstNumber = (int) Math.round(Math.random() * 8) + 1;
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