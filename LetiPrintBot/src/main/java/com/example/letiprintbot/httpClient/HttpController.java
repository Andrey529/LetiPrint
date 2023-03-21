package com.example.letiprintbot.httpClient;

import com.google.gson.Gson;
import com.google.gson.JsonObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpController {


    public String getFilePath(String botToken, String fileId) throws IOException {
        URL obj = new URL("https://api.telegram.org/bot" + botToken + "/getFile?file_id=" + fileId);
        Gson gson = new Gson();
        HttpURLConnection con = (HttpURLConnection) obj.openConnection();
        con.setRequestMethod("GET");
        con.setRequestProperty("Content-Type", "application/json");
        con.setDoOutput(true);
        int responseCode = con.getResponseCode();
        if (responseCode == HttpURLConnection.HTTP_OK) { //success
            BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
            String inputLine;
            StringBuilder response = null;
            while ((inputLine = in.readLine()) != null) {
                if (response != null)
                    response.append(inputLine);
                else
                    response = new StringBuilder(inputLine);
            }
            in.close();
            assert response != null;
            JsonObject jsonObject = gson.fromJson(response.toString(), JsonObject.class);
            return jsonObject.getAsJsonObject("result").getAsJsonPrimitive("file_path").toString();
        }

        return "404";
    }

    private String makeDownloadLink(String filePath, long chatId, String botToken) {

        String downloadLink = "https://api.telegram.org/file/bot" + botToken + "/" + filePath.substring(1, filePath.length() - 1);
        System.out.println(downloadLink);
        return downloadLink;
    }

    public void sendDownloadLink(String filePath, long chatId, String botToken) {
        makeDownloadLink(filePath, chatId, botToken);
    }

}
