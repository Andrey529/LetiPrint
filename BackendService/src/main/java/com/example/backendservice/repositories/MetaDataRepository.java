package com.example.backendservice.repositories;

import com.example.backendservice.models.MetaData;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Component
public interface MetaDataRepository extends JpaRepository<MetaData, String> {

    @Query("SELECT fileId FROM MetaData")
    List<Short> getFileIds();

    MetaData getMetaDataByFileId(String fileId);

    @Query(value = "SELECT COUNT(*) FROM files", nativeQuery = true)
    int countOfLines();

    @Transactional
    @Modifying
    @Query(value = "DELETE FROM files WHERE created_at < CURRENT_TIMESTAMP - INTERVAL '24 hours'",nativeQuery = true)
    void deleteOldRecords();





}