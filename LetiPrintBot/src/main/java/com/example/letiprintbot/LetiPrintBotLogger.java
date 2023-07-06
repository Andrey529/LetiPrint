package com.example.letiprintbot;

import com.example.letiprintbot.service.LetiPrintBot;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public abstract class LetiPrintBotLogger {
    public static final Logger logger = LoggerFactory.getLogger(LetiPrintBot.class);

    public static void loggingReceivedDoc(String username,String filename){
        logger.info("Username " + username + " uploaded file with filename " + filename);
    }

    public static void loggingAcceptedDoc(String username,String fileId){
        logger.info("Username " + username + " was accepted print file with fileId " + fileId);
    }

    public static void loggingCancelledDoc(String username,String filename){
        logger.info("Username " + username + " was cancelled print file with filename " + filename);
    }

}
