package com.example.backendservice.models;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name = "files")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class MetaData {

    @Id
    private short fileId;

    @Column(name = "user_id")
    private String userId;

    @Column(name = "file_link")
    private String fileLink;

    @Column(name = "file_type")
    private String fileType;

    @Column(name = "file_name")
    private String fileName;

    @Override
    public String toString() {
        return
                "fileId=" + fileId +
                ", userId='" + userId + '\'' +
                ", fileLink='" + fileLink + '\'' +
                ", fileType='" + fileType + '\'' +
                ", fileName='" + fileName + '\'' ;
    }
}