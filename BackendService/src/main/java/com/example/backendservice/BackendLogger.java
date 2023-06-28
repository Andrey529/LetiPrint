package com.example.backendservice;

import com.example.backendservice.controller.BackendController;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Map;

public abstract class BackendLogger {

    public static final Logger logger = LoggerFactory.getLogger(BackendController.class);

    public static void loggingIdGenerator(String generatedId){
        logger.info("New generated id for this session:" + generatedId);
    }

    public static void loggingHttpRequest(String methodType, String target, String body, Map<String,String> requestParameters){
        logger.info("New request:");
        logger.info("    method:" + methodType);
        logger.info("    target:" + target);
        logger.info("    body:" + body);
        if (requestParameters != null)
        logger.info("    Request parameters:" + requestParameters);
        else
            logger.info("    Request parameters:" );
    }

    public static void loggingUnsuccessfulRequest(String methodType, String target, String body, Map<String,String> requestParameters){
        logger.warn("Unsuccessful request:");
        logger.warn("    method:" + methodType);
        logger.warn("    target:" + target);
        logger.warn("    body:" + body);
        logger.warn("    Request parameters:" + requestParameters);
        logger.warn("No such file id in the database");
    }


}
