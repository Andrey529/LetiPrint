package com.example.letiprintbot.httpClient;

import com.example.letiprintbot.metaData.MetaData;
import com.google.gson.Gson;
import com.google.gson.JsonObject;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
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

    public String sendMetadata(String botToken, String filePath, String filename) throws IOException {
        MetaData metaData = new MetaData();
        URL obj = new URL("http://localhost:8010/metaData");
        JSONObject jObj = metaData.makeJson(botToken,filePath,filename);
        HttpURLConnection con = (HttpURLConnection) obj.openConnection();
        con.setRequestMethod("POST");
        con.setRequestProperty("Content-Type", "application/json");
        con.setDoOutput(true);
        OutputStream os = con.getOutputStream();
        byte[] out = jObj.toString().getBytes();
        os.write(out);
        os.flush();
        os.close();

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
            return response.toString();
        }
        else
            return "Ошибка";
    }
}