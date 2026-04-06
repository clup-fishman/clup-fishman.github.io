/**
 * Communicates with backend API for trip and authentication operations.
 * Uses environment configuration for API endpoints.
 */

import { Inject, Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Trip } from '../models/trip';
import { User } from '../models/user';
import { AuthResponse } from '../models/auth-response';
import { BROWSER_STORAGE } from '../storage';
import { environment } from '../../environments/environment';

@Injectable({
  providedIn: 'root',
})
export class TripDataService {
  private readonly baseUrl = environment.apiBaseUrl;
  private readonly tripsUrl = `${this.baseUrl}/trips`;

  constructor(
    private http: HttpClient,
    @Inject(BROWSER_STORAGE) private storage: Storage,
  ) {}

  getTrips(): Observable<Trip[]> {
    return this.http.get<Trip[]>(this.tripsUrl);
  }

  addTrip(formData: Trip): Observable<Trip> {
    return this.http.post<Trip>(this.tripsUrl, formData);
  }

  getTrip(tripCode: string): Observable<Trip> {
    return this.http.get<Trip>(this.tripsUrl + '/' + tripCode);
  }

  updateTrip(formData: Trip): Observable<Trip> {
    return this.http.put<Trip>(this.tripsUrl + '/' + formData.code, formData);
  }

  // Call to our /login endpoint, returns JWT
  login(user: User, passwd: string): Observable<AuthResponse> {
    return this.handleAuthAPICall('login', user, passwd);
  }
  // Call to our /register endpoint, creates user and returns JWT
  register(user: User, passwd: string): Observable<AuthResponse> {
    return this.handleAuthAPICall('register', user, passwd);
  }

  // Helper method to process both login and register methods
  private handleAuthAPICall(
    endpoint: string,
    user: User,
    passwd: string,
  ): Observable<AuthResponse> {
    const formData = {
      name: user.name,
      email: user.email,
      password: passwd,
    };

    return this.http.post<AuthResponse>(
      this.baseUrl + '/' + endpoint,
      formData,
    );
  }
}
