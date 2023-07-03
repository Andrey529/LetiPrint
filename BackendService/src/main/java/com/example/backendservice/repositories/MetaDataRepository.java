package com.example.backendservice.repositories;

import com.example.backendservice.models.MetaData;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface MetaDataRepository extends JpaRepository<MetaData, String> {

    @Query("SELECT fileId FROM MetaData")
    List<Short> getFileIds();

    MetaData getMetaDataByFileId(String fileId);



}